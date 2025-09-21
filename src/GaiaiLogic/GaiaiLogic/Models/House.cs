namespace GaiaiLogic.Models {

    internal record House {

        public string District { get; init; } = "";

        public string Name { get; set; } = "";

        public string Shape { get; set; } = "";

        public int X { get; set; }

        public int Y { get; set; }

        public int Rotation { get; set; }

        public IEnumerable<HouseFuse> Fuses { get; set; } = [];

    }

}