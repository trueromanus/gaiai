namespace GaiaiLogic.Models {

    public record House {

        public string District { get; init; } = "";

        public string Name { get; set; } = "";

        public string Shape { get; set; } = "";

        public int X { get; set; }

        public int Y { get; set; }

        public int Rotation { get; set; }

        public int FusesCount { get; set; }

        public IEnumerable<int> Fuses { get; set; } = new List<int> ();

    }

}