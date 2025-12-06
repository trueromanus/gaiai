namespace GaiaiLogic.Models {

    internal record Road {

        public string Title { get; init; } = "";

        public string District { get; init; } = "";

        public int X1 { get; init; }

        public int Y1 { get; init; }

        public int X2 { get; init; }

        public int Y2 { get; init; }

    }

}
