namespace GaiaiLogic.Models {

    public record CitizenSchedule {

        public TimeSpan Time { get; init; }

        public string Location { get; init; } = "";

        public string HandleCode { get; set; } = "";

        public CitizenScheduleTransport Transport { get; set; }

    }

}