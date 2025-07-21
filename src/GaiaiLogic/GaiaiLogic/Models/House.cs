namespace GaiaiLogic.Models {

    internal record House {

        public string District { get; init; } = "";

        public IEnumerable<HouseShape> Houses { get; set; } = Enumerable.Empty<HouseShape> ();

    }

}
