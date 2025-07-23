namespace GaiaiLogic.Interactive {

    internal record ColorTimes ( int green, int yellow, int red );

    internal class GameTrafficLight {

        private ColorTimes m_currentState = new ColorTimes ( 0, 0, 0 );

        private readonly ColorTimes m_correctState;

        public string Title { get; internal set; } = "";

        public IEnumerable<string> AffectedHouses { get; internal set; } = Enumerable.Empty<string> ();

        public bool Correct => m_correctState == m_currentState;

        public GameTrafficLight ( string title, IEnumerable<string> affectedHouses ) {
            var random = new Random ( (int) ( DateTime.UtcNow - new DateTime ( 1970, 1, 1 ) ).TotalSeconds );
            m_correctState = new ColorTimes ( random.Next ( 1, 30 ), random.Next ( 1, 30 ), random.Next ( 1, 30 ) );
            m_currentState = m_correctState;

            Title = title;
            AffectedHouses = affectedHouses;
        }



    }

}
