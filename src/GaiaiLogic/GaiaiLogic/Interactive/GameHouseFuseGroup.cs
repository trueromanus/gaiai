namespace GaiaiLogic.Interactive {

    internal class GameHouseFuseGroup {

        public int Width { get; set; }

        public Dictionary<int, GameHouseFuse> Triggers { get; set; } = new Dictionary<int, GameHouseFuse> ();

    }

}
