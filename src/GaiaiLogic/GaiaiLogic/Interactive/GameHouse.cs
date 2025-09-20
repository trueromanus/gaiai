using GaiaiLogic.Models;

namespace GaiaiLogic.Interactive {

    internal class GameHouse {

        private List<GameHouseFuse> m_fuses = [];

        public string Name { get; internal set; }

        public string Shape { get; internal set; }

        public GamePosition Position { get; internal set; }

        public int FusesCount { get; internal set; }

        public GameHouse ( House house ) {
            Name = house.Name;
            Shape = house.Shape;
            Position = new GamePosition ( house.X, house.Y, house.Rotation );
            FusesCount = house.FusesCount;
            m_fuses.AddRange ( house.Fuses.Select ( a => new GameHouseFuse { Enabled = true, Position = a } ) );
        }

    }

}
