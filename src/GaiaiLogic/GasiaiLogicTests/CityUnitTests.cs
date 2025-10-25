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
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub() );

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
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

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
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

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
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            city.AddCitizen ( citizen );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

            // assert
            Assert.False ( citizen.InsideOriginalLocation () );
            Assert.Equal ( 0, citizen.Craziness );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_NotCorrectTrafficLight_CitizensCollision_OnCars () {
            // arrange
            var city = new City ();
            city.SetEnableRandomized ( false );
            var citizen1 = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Car
                    }
                }
            );
            var citizen2 = new GameCitizen (
                "loc3",
                "cit2",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Car
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen1 );
            city.AddCitizen ( citizen2 );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

            // assert
            Assert.False ( citizen1.InsideOriginalLocation () );
            Assert.Equal ( 25, citizen1.Craziness );
            Assert.Equal ( 25, citizen2.Craziness );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_NotCorrectTrafficLight_CitizensCollision_OnBuses () {
            // arrange
            var city = new City ();
            city.SetEnableRandomized ( false );
            var citizen1 = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Bus
                    }
                }
            );
            var citizen2 = new GameCitizen (
                "loc3",
                "cit2",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Bus
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen1 );
            city.AddCitizen ( citizen2 );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

            // assert
            Assert.False ( citizen1.InsideOriginalLocation () );
            Assert.Equal ( 15, citizen1.Craziness );
            Assert.Equal ( 15, citizen2.Craziness );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_NotCorrectTrafficLight_CitizensCollision_OnCarAndBus () {
            // arrange
            var city = new City ();
            city.SetEnableRandomized ( false );
            var citizen1 = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Car
                    }
                }
            );
            var citizen2 = new GameCitizen (
                "loc3",
                "cit2",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Bus
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen1 );
            city.AddCitizen ( citizen2 );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

            // assert
            Assert.False ( citizen1.InsideOriginalLocation () );
            Assert.Equal ( 25, citizen1.Craziness );
            Assert.Equal ( 15, citizen2.Craziness );
        }

        [Fact]
        public void City_Completed_HitTrafficLight_NotCorrectTrafficLight_CitizensCollision_WalkAndCar () {
            // arrange
            var city = new City ();
            city.SetEnableRandomized ( false );
            var citizen1 = new GameCitizen (
                "loc1",
                "cit1",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.Car
                    }
                }
            );
            var citizen2 = new GameCitizen (
                "loc3",
                "cit2",
                new List<CitizenSchedule> {
                    new CitizenSchedule {
                        Location = "house1",
                        Time = new TimeSpan ( 10, 0, 0 ),
                        Transport = CitizenScheduleTransport.NoTransport
                    }
                }
            );
            var trafficLight = new GameTrafficLight (
                new TrafficLight { Title = "trafficlight1", AffectedHouses = ["house1"] }
            );
            trafficLight.ChangeState ( 0, 0, 0 );
            city.AddCitizen ( citizen1 );
            city.AddCitizen ( citizen2 );
            city.AddTrafficLight ( trafficLight );

            // act
            city.ProcessEvents ( new TimeSpan ( 10, 0, 0 ), new TriggersHub () );

            // assert
            Assert.False ( citizen1.InsideOriginalLocation () );
            Assert.Equal ( 25, citizen1.Craziness );
            Assert.Equal ( 100, citizen2.Craziness );
        }

    }

}
