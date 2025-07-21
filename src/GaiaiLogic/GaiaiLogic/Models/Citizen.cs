namespace GaiaiLogic.Models {

    internal record Citizen {

        public string Title { get; init; } = "";

        public string OriginalLocation { get; init; } = "";

        public IEnumerable<CitizenSchedule> Schedule { get; init; } = Enumerable.Empty<CitizenSchedule> ();

    }

}
