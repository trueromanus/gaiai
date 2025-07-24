namespace GaiaiLogic.Interactive {

    internal record ColorTimes ( int green, int yellow, int red );

    internal class GameTrafficLight {

        private const string Green = "green";

        private const string Red = "red";

        private const string Yellow = "yellow";

        private ColorTimes m_currentState = new ColorTimes ( 0, 0, 0 );

        private readonly ColorTimes m_correctState;

        public string Title { get; internal set; } = "";

        public ColorTimes CurrentState => m_currentState;

        public ColorTimes CorrectState => m_correctState;

        public IEnumerable<string> AffectedHouses { get; internal set; } = Enumerable.Empty<string> ();

        public bool Correct => m_correctState == m_currentState;

        public GameTrafficLight ( string title, IEnumerable<string> affectedHouses ) {
            var random = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );
            m_correctState = new ColorTimes ( random.Next ( 1, 30 ), random.Next ( 1, 30 ), random.Next ( 1, 30 ) );
            m_currentState = m_correctState;

            Title = title;
            AffectedHouses = affectedHouses;
        }

        public void ChangeState ( int green, int yellow, int red ) {
            m_currentState = new ColorTimes ( green, red, yellow );
        }

        public void ParseContent ( string content ) {
            var lines = content.Split ( "\n" )
                .Select ( line => line.Trim ().ToLowerInvariant () )
                .Where ( a => !string.IsNullOrEmpty ( a ) )
                .ToList ();
            var green = 0;
            var red = 0;
            var yellow = 0;
            foreach ( var line in lines ) {
                if ( line.StartsWith ( Green ) ) green = GetValue ( Green, line );
                if ( line.StartsWith ( Red ) ) red = GetValue ( Red, line );
                if ( line.StartsWith ( Yellow ) ) yellow = GetValue ( Yellow, line );
            }

            static int GetValue ( string color, string line ) {
                return Convert.ToInt32 ( line.Replace ( color, "" ) );
            }

            m_currentState = new ColorTimes ( green, yellow, red );
        }

    }

}
