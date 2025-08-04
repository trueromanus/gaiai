using GaiaiLogic.Models;

namespace GaiaiLogic.Interactive {

    internal class GameCitizen {

        private bool m_active = true;

        private string m_currentLocation = "";

        private CitizenScheduleTransport m_currentLocationTransport = CitizenScheduleTransport.NoTransport;

        private int m_craziness = 0;

        private string? m_incidentHandler;

        public string Title { get; internal set; } = "";

        public string OriginalLocation { get; internal set; } = "";

        public string CurrentLocation => m_currentLocation;

        public CitizenScheduleTransport CitizenScheduleTransport => m_currentLocationTransport;

        public GameCitizenIncidentMode IncidentMode { get; set; }

        public IEnumerable<CitizenSchedule> Schedule { get; internal set; } = Enumerable.Empty<CitizenSchedule> ().ToList ();

        public bool Active => m_active;

        public int Craziness => m_craziness;

        public GameCitizen ( string originalLocation, string title, IEnumerable<CitizenSchedule> schedule, string? incidentHandler = default ) {
            OriginalLocation = originalLocation;
            Title = title;
            Schedule = schedule.ToList ();
            m_currentLocation = originalLocation;
            m_incidentHandler = incidentHandler;
        }

        public void ChangeLocation ( string newLocation, CitizenScheduleTransport newTransport ) {
            m_currentLocation = newLocation;
            m_currentLocationTransport = newTransport;
        }

        public void IncreaseCraziness ( int value ) {
            m_craziness += value;
            if ( m_craziness > 100 ) m_craziness = 100;

            if ( m_craziness == 100 ) m_active = false;
        }

        public bool InsideOriginalLocation () => m_currentLocation == OriginalLocation;

        public void CrossIncidentHappened ( GameCitizen gameCitizen ) {
            if ( !string.IsNullOrEmpty ( m_incidentHandler ) ) {
                //TODO: execute script
                return;
            }

            // case when crossed with any object located in car
            if ( m_currentLocationTransport == CitizenScheduleTransport.Car && IncidentMode is GameCitizenIncidentMode.None ) {
                IncreaseCraziness ( 20 );
                IncidentMode = GameCitizenIncidentMode.CarAccident;
                return;
            }

            // case when crossed with any object located in bus
            if ( m_currentLocationTransport == CitizenScheduleTransport.Bus && IncidentMode is GameCitizenIncidentMode.None ) {
                IncreaseCraziness ( 10 );
                IncidentMode = GameCitizenIncidentMode.BusAccident;
                return;
            }

            // case when crossed with bus or car and citizen not in transport
            if ( ( gameCitizen.CitizenScheduleTransport is CitizenScheduleTransport.Car or CitizenScheduleTransport.Bus ) && IncidentMode is GameCitizenIncidentMode.None ) {
                IncreaseCraziness ( 100 );
                IncidentMode = gameCitizen.CitizenScheduleTransport switch {
                    CitizenScheduleTransport.Car => GameCitizenIncidentMode.CarAccident,
                    CitizenScheduleTransport.Bus => GameCitizenIncidentMode.BusAccident,
                    _ => GameCitizenIncidentMode.None
                };
                return;
            }
        }

    }

}
