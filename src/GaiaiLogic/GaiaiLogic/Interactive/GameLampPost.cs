namespace GaiaiLogic.Interactive {

    internal record LampPostItem ( bool Mode, TimeOnly Minutes );

    internal class GameLampPost {

        private const string TurnOn = "turnon";

        private const string TurnOff = "turnoff";

        private readonly int m_correctState;

        private readonly int m_currentState;

        private bool m_turnOn = true;

        public string Title { get; internal set; } = "";

        public List<LampPostItem> CurrentSchedule { get; internal set; }

        public IEnumerable<string> AffectedHouses { get; internal set; } = Enumerable.Empty<string> ();

        public GameLampPost ( string title, IEnumerable<string> affectedHouses ) {
            Title = title ?? throw new ArgumentNullException ( nameof ( title ) ); ;
            AffectedHouses = affectedHouses ?? throw new ArgumentNullException ( nameof ( affectedHouses ) );
            var random = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );

            m_correctState = random.Next ( 30, 70 );
            m_currentState = m_correctState;

            var time = new TimeOnly ( 21, 00 ).AddHours ( random.Next ( 1, 7 ) );

            CurrentSchedule = new List<LampPostItem> {
                new LampPostItem (true, time),
                new LampPostItem (false, time.AddMinutes(m_correctState))
            };
        }

        public bool Correct => m_currentState == m_correctState;

        public bool IsTurnOn => m_turnOn;

        public void ParseContent ( string content ) {

        }

    }

}
