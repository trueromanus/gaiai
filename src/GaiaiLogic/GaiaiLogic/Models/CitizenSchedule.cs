namespace GaiaiLogic.Models {

    public record CitizenSchedule {

        public TimeSpan Time { get; init; }

        public string Location { get; init; } = "";

    }

}