using GaiaiLogic.Interactive;

namespace GaiaiLogic {

    internal class City {

        public List<GameCitizen> m_citizens = [];

        public Dictionary<string, GameTrafficLight> m_trafficLight = [];

        private Random m_randomCollisions = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );

        public void ProcessEvents ( TimeSpan time ) {
            var activeCitizens = m_citizens
                .Where ( a => a.Active )
                .ToArray ();

            foreach ( var activeCitizen in activeCitizens ) {
                var scheduleStep = activeCitizen.Schedule.FirstOrDefault ( a => a.Time == time );
                if ( scheduleStep != null ) {
                    activeCitizen.ChangeLocation ( scheduleStep.Location );

                    // if related to location trafic light will be not in correct state
                    // citizen get or 5 craziness and in random case is incident
                    if ( m_trafficLight.TryGetValue ( activeCitizen.CurrentLocation, out var trafficLight ) ) {
                        if ( !trafficLight.Correct ) {
                            activeCitizen.IncreaseCraziness ( 5 );
                            //TODO: in random case is it happened incident
                        }
                    }

                    // if some other citizen will be in same location we need to make crash
                    if ( !activeCitizen.InsideOriginalLocation () ) {
                        var otherCitizensInSamePlace = activeCitizens
                            .Where ( a => a != activeCitizen && a.CurrentLocation == activeCitizen.CurrentLocation )
                            .ToList ();
                        foreach ( var otherCitizenInSamePlace in otherCitizensInSamePlace ) {
                            if ( m_randomCollisions.Next ( 4 ) == 1 ) {
                                activeCitizen.IncreaseCraziness( 100 );
                                otherCitizenInSamePlace.IncreaseCraziness ( 100 );
                            }
                        }
                    }
                }
            }

            // TODO: if some from citizens will be in location where another citizen and any city objects is not correct it must be happened incident
        }

        /// <summary>
        /// Finish all runned processed (if it exists of course).
        /// </summary>
        public void FinishAllProcesses () {

        }

    }

}
