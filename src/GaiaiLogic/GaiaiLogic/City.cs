using GaiaiLogic.Interactive;
using GaiaiLogic.Loaders;

namespace GaiaiLogic {

    internal class City {

        private List<GameCitizen> m_citizens = [];

        private List<GameTrafficLight> m_trafficLight = [];

        private Dictionary<string, GameHouse> m_houses = [];

        private List<GameLampPost> m_lampPosts = [];

        private ILookup<string, GameRoad>? m_roads = null;

        private Random m_randomCollisions = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );

        private bool m_enableRandomized = true;

        private int GetRandomCollisisons () => m_enableRandomized ? m_randomCollisions.Next ( 4 ) : 1;

        public void SetEnableRandomized ( bool enabled ) => m_enableRandomized = enabled;

        public void ProcessEvents ( TimeSpan time, TriggersHub triggersHub ) {
            var activeCitizens = m_citizens
                .Where ( a => a.Active )
                .ToArray ();

            foreach ( var activeCitizen in activeCitizens ) {
                var scheduleStep = activeCitizen.Schedule.FirstOrDefault ( a => a.Time == time );
                if ( scheduleStep == null ) continue;

                activeCitizen.ChangeLocation ( scheduleStep.Location, scheduleStep.Transport );

                var haveInCorrectess = false;

                // if related to location trafic light will be not in correct state citizen we increase craziness
                var trafficLights = m_trafficLight.Where ( a => a.AffectedHouses.Any ( b => b == scheduleStep.Location ) );
                foreach ( var trafficLight in trafficLights ) {
                    if ( !trafficLight.Correct ) {
                        activeCitizen.IncreaseCraziness ( 5 );
                        haveInCorrectess = true;
                    }
                }

                // if related to location lamp post will be not in correct state citizen we increase craziness
                var lampPosts = m_lampPosts.Where ( a => a.AffectedHouses.Any ( b => b == scheduleStep.Location ) );
                foreach ( var lampPost in lampPosts ) {
                    if ( !lampPost.Correct || !lampPost.IsTurnOn ( time ) ) {
                        activeCitizen.IncreaseCraziness ( 2 );
                        haveInCorrectess = true;
                    }
                }

                // if some other citizen will be in same location we need to make crash
                if ( haveInCorrectess && !activeCitizen.InsideOriginalLocation () ) {
                    var otherCitizensInSamePlace = activeCitizens
                        .Where ( a => activeCitizen.Title != a.Title && !a.InsideOriginalLocation () && a.CurrentLocation == activeCitizen.CurrentLocation )
                        .ToList ();
                    foreach ( var otherCitizenInSamePlace in otherCitizensInSamePlace ) {
                        if ( GetRandomCollisisons () == 1 ) {
                            activeCitizen.CrossIncidentHappened ( otherCitizenInSamePlace );
                            otherCitizenInSamePlace.CrossIncidentHappened ( activeCitizen );
                        }
                    }
                }

                if ( activeCitizen.InsideOriginalLocation () ) {
                    var house = m_houses[activeCitizen.OriginalLocation];
                    if ( house != null ) {
                        var multipleLevel = 2 * house.NotCorrectLevel ();
                        if ( multipleLevel > 0 ) activeCitizen.IncreaseCraziness ( multipleLevel );
                    }
                }
            }
        }

        /// <summary>
        /// Finish all runned processed (if it exists of course).
        /// </summary>
        public void FinishAllProcesses () {

        }

        public void AddTrafficLight ( GameTrafficLight gameTrafficLight ) => m_trafficLight.Add ( gameTrafficLight );

        public void AddCitizen ( GameCitizen citizen ) => m_citizens.Add ( citizen );

        public void FillData ( LoadedStaticItems loadedStaticItems ) {
            m_citizens.Clear ();
            m_trafficLight.Clear ();
            m_lampPosts.Clear ();

            foreach ( var item in loadedStaticItems.Houses ) m_houses.Add ( item.Name, new GameHouse ( item ) );
            foreach ( var item in loadedStaticItems.TrafficLights ) m_trafficLight.Add ( new GameTrafficLight ( item ) );
            m_roads = loadedStaticItems.Roads
                .Select ( a => new { a.District, model = new GameRoad ( a ) } )
                .ToLookup ( a => a.District, a => a.model );
        }

        /// <summary>
        /// Just for tests
        /// </summary>
        public IEnumerable<GameHouse> GetHouses () => m_houses.Values.ToList ();

        public IEnumerable<GameTrafficLight> GetTrafficLights () => m_trafficLight.ToList ();

        public IEnumerable<GameRoad> GetRoadsForDistrict ( string district ) {
            if ( m_roads == null ) return Enumerable.Empty<GameRoad> ();
            if ( !m_roads.Contains ( district ) ) return Enumerable.Empty<GameRoad> ();

            return m_roads[district];
        }

    }

}
