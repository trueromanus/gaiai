using GaiaiLogic;
using GaiaiLogic.Interactive;
using GaiaiLogic.Models;

namespace GaiaiLogicTests {

    public class CityUnitTests {

        [Fact]
        public void City_Completed_ChangeLocationOnSchedule () {
            // arrange
            var city = new City ();
            var citizen = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "loc2",
                        Time = new TimeSpan ( 10,0,0 ),
                    }
                }
            );
            city.AddCitizen ( citizen );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ) );

            // assert
            Assert.False ( citizen.InsideOriginalLocation () );
        }

        [Fact]
        public void City_Completed_NotChangeLocationOnSchedule () {
            // arrange
            var city = new City ();
            var citizen = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "loc2",
                        Time = new TimeSpan ( 10, 5, 0 )
                    }
                }
            );
            city.AddCitizen ( citizen );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ) );

            // assert
            Assert.True ( citizen.InsideOriginalLocation () );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_NotCorrectTrafficLight () {
            // arrange
            var city = new City ();
            var citizen = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 )
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                "trafficlight1",
                ["house1"]
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ) );

            // assert
            Assert.False ( citizen.InsideOriginalLocation () );
            Assert.Equal ( 5, citizen.Craziness );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_CorrectTrafficLight () {
            // arrange
            var city = new City ();
            var citizen = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 )
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                "trafficlight1",
                ["house1"]
            );
            city.AddCitizen ( citizen );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ) );

            // assert
            Assert.False ( citizen.InsideOriginalLocation () );
            Assert.Equal ( 0, citizen.Craziness );
        }

    }

}
