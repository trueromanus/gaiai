namespace GaiaiLogic.Interactive {

    internal class GameLampPost {

        private string m_title;

        private IEnumerable<string> m_affectedHouses = new List<string> ();

        public GameLampPost ( string title, IEnumerable<string> affectedHouses ) {
            m_title = title ?? throw new ArgumentNullException ( nameof ( title ) ); ;
            m_affectedHouses = affectedHouses ?? throw new ArgumentNullException ( nameof ( affectedHouses ) );
        }

        public bool Correct => true;

        public IEnumerable<string> AffectedHouses => m_affectedHouses;

    }

}
