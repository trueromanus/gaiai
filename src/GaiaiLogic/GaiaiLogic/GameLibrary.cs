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

            var staticItems = m_dataLoader.LoadStaticItems ( language );
            m_shift.FillStaticItems ( staticItems );

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

        /// <summary>
        /// Just for tests
        /// </summary>
        public static IEnumerable<(string shape, int x, int y, int rotate)> GetHouses () {
            var result = new List<(string shape, int x, int y, int rotate)> ();
            foreach ( var house in m_shift!.GetHouses () ) {
                result.Add ( (house.Shape, house.Position.x, house.Position.y, house.Position.rotation) );
            }

            return result;
        }

        public static IEnumerable<(string shape, int x, int y)> GetTrafficeLights () {
            var result = new List<(string shape, int x, int y)> ();
            foreach ( var house in m_shift!.GetTrafficLights () ) {
                result.Add ( ("", house.Position.x, house.Position.y) );
            }

            return result;
        }

    }

}
