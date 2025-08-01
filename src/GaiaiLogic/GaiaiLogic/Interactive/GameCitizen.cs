using GaiaiLogic.Models;

namespace GaiaiLogic.Interactive {

    internal class GameCitizen {

        private bool m_active = true;

        private string m_currentLocation = "";

        private int m_craziness = 0;

        public string Title { get; internal set; } = "";

        public string OriginalLocation { get; internal set; } = "";

        public string CurrentLocation => m_currentLocation;

        public GameCitizenIncidentMode IncidentMode { get; set; }

        public IEnumerable<CitizenSchedule> Schedule { get; internal set; } = Enumerable.Empty<CitizenSchedule> ().ToList ();

        public bool Active => m_active;

        public int Craziness => m_craziness;

        public GameCitizen ( string originalLocation, string title, IEnumerable<CitizenSchedule> schedule ) {
            OriginalLocation = originalLocation;
            Title = title;
            Schedule = schedule.ToList ();
            m_currentLocation = originalLocation;
        }

        public void ChangeLocation ( string newLocation ) => m_currentLocation = newLocation;

        public void IncreaseCraziness ( int value ) {
            m_craziness += value;
            if ( m_craziness > 100 ) m_craziness = 100;

            if ( m_craziness == 100 ) m_active = false;
        }

        public bool InsideOriginalLocation () => m_currentLocation == OriginalLocation;

        public void CarIncidentHappened() {
            if ( IncidentMode is GameCitizenIncidentMode.None and not GameCitizenIncidentMode.CarAccident ) {
                IncreaseCraziness ( 20 );
                IncidentMode = GameCitizenIncidentMode.CarAccident;
            }
        }

    }

}
