using GaiaiLogic.Loaders;

namespace GaiaiLogic {

    public static class GameLibrary {

        private static Shift? m_shift = null;
        private static DataLoader? m_dataLoader = null;
        private static TriggersHub? m_triggersHub = null;

        public static bool InitializeGame ( string language ) {
            m_dataLoader = new DataLoader ();
            m_triggersHub = new TriggersHub ();
            m_shift = new Shift ( m_triggersHub );

            m_dataLoader.LoadStaticItems ( language );

            return true;
        }

        public static bool RunTimer () {
            m_shift?.Run ();
            return true;
        }

        public static bool StopTimer () {
            m_shift?.Stop ();
            return true;
        }

    }

}
