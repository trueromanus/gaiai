namespace GaiaiLogic.Interactive {

    internal record LampPostItem ( bool Mode, TimeSpan Minutes );

    internal class GameLampPost {

        private const string TurnOn = "turnon";

        private const string TurnOff = "turnoff";

        private readonly int m_correctState;

        private readonly int m_currentState;

        public string Title { get; internal set; } = "";

        public List<LampPostItem> CurrentSchedule { get; internal set; }

        public IEnumerable<string> AffectedHouses { get; internal set; } = Enumerable.Empty<string> ();

        public GameLampPost ( string title, IEnumerable<string> affectedHouses ) {
            Title = title ?? throw new ArgumentNullException ( nameof ( title ) ); ;
            AffectedHouses = affectedHouses ?? throw new ArgumentNullException ( nameof ( affectedHouses ) );
            var random = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );

            m_correctState = random.Next ( 30, 70 );
            m_currentState = m_correctState;

            var time = new TimeSpan ( 21, 0, 0 ) + new TimeSpan ( 21 + random.Next ( 1, 7 ), 0, 0 );

            CurrentSchedule = new List<LampPostItem> {
                new LampPostItem (true, time),
                new LampPostItem (false, time + TimeSpan.FromMinutes( m_correctState))
            };
        }

        public bool Correct => m_currentState == m_correctState;

        public bool IsTurnOn ( TimeSpan time ) {
            var schedule = CurrentSchedule
                .OrderBy ( a => a.Minutes );

            var leftLimit = schedule.FirstOrDefault ( a => a.Minutes <= time );
            if ( leftLimit == null ) return false;

            return leftLimit.Mode;
        }

        public void ParseContent ( string content ) {
            CurrentSchedule.Clear ();

            var lines = content.Split ( "\n" )
                .Select ( line => line.Trim ().ToLowerInvariant () )
                .Where ( a => !string.IsNullOrEmpty ( a ) )
                .ToList ();
            foreach ( var line in lines ) {
                if ( !( line.StartsWith ( TurnOff ) || line.StartsWith ( TurnOn ) ) ) continue;

                var turnOn = line.StartsWith ( TurnOn );
                TimeSpan timeValue = TimeSpan.Zero;

                var span = line.AsSpan ();
                var index = span.IndexOf ( ' ' );
                var slice = span.Slice ( index );
                timeValue = TimeSpan.Parse ( slice );

                CurrentSchedule.Add ( new LampPostItem ( turnOn, timeValue ) );
            }
        }

    }

}
