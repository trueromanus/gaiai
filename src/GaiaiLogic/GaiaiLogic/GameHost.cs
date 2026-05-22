using GaiaiLogic.Loaders;
using GaiaiLogic.Translate;
using System.Numerics;

namespace GaiaiLogic
{

    public class GameHost
    {

        private readonly Shift m_shift;
        private readonly DataLoader m_dataLoader;
        private readonly TriggersHub m_triggersHub;
        private readonly Translator m_translator;

        public GameHost()
        {
            m_dataLoader = new DataLoader();
            m_triggersHub = new TriggersHub();
            m_shift = new Shift(m_triggersHub);

            m_translator = new Translator();
            
        }

        public bool InitializeGame(string language)
        {
            var staticItems = m_dataLoader.LoadStaticItems(language);
            m_shift.FillStaticItems(staticItems);

            m_translator.LoadTranslation(language);
            return true;
        }

        internal TriggersHub? TriggersHub => m_triggersHub;

        internal Translator Translator => m_translator;

        public bool RunTimer()
        {
            m_shift?.Run();
            return true;
        }

        public bool StopTimer()
        {
            m_shift?.Stop();
            return true;
        }

        /// <summary>
        /// Just for tests
        /// </summary>
        public IEnumerable<(string shape, int x, int y, int rotate)> GetHouses()
        {
            var result = new List<(string shape, int x, int y, int rotate)>();
            foreach (var house in m_shift!.GetHouses())
            {
                result.Add((house.Shape, house.Position.x, house.Position.y, house.Position.rotation));
            }

            return result;
        }

        public IEnumerable<(string shape, int x, int y)> GetTrafficeLights()
        {
            var result = new List<(string shape, int x, int y)>();
            foreach (var house in m_shift!.GetTrafficLights())
            {
                result.Add(("", house.Position.x, house.Position.y));
            }

            return result;
        }

        public IEnumerable<(Vector2 start, Vector2 finish)> GetRoads(string district)
        {
            var roads = m_shift!.GetCity().GetRoadsForDistrict(district);
            return roads.Select(a => (a.Start, a.Finish));
        }

    }

}
