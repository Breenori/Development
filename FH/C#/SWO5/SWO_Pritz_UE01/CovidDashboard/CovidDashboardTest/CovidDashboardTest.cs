using Microsoft.VisualStudio.TestTools.UnitTesting;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using System.Collections.Generic;

namespace SWO5.Dashboard.Test
{
    [TestClass]
    public class CovidDashboardTest
    {
        ICovidDashboard dashboard;
        IList<User> test_users;

        [TestInitialize]
        public void Initialize()
        {
            dashboard = CovidDashboardFactory.CreateCovidDashboard();
            test_users = new List<User>();
            //dashboard.FillFromCSV(@"../../../../CovidFaelle_Timeline_GKZ.csv");
            test_users.Add(new User { Name = "admin", Password = "geheim" });
            test_users.Add(new User { Name = "AddUser", Password = "test_adduser" });
            test_users.Add(new User { Name = "RemoveUser", Password = "test_removeuser" });
            test_users.Add(new User { Name = "UpdateUser", Password = "test_updateuser" });
            dashboard.RemoveUser(test_users[1].Name, test_users[1].Password);
            dashboard.AddUser(test_users[2].Name, test_users[2].Password);
            dashboard.AddUser(test_users[3].Name, test_users[3].Password);
        }

        [TestMethod]
        public void TestLogin()
        {
            // given
            User u = test_users[0];

            // when

            // then
            Assert.AreEqual(dashboard.Login(u.Name, u.Password), true);
        }

        [TestMethod]
        public void TestAddUser()
        {
            // given
            User u = test_users[1];

            // when
            bool before = dashboard.Login(u.Name, u.Password);
            dashboard.AddUser(u.Name, u.Password);
            bool after = dashboard.Login(u.Name, u.Password);

            // then
            Assert.AreEqual(before, false);
            Assert.AreEqual(after, true);
        }

        [TestMethod]
        public void TestRemoveUser()
        {
            // given
            User u = test_users[2];

            // when
            bool before = dashboard.Login(u.Name, u.Password);
            dashboard.RemoveUser(u.Name, u.Password);
            bool after = dashboard.Login(u.Name, u.Password);

            // then
            Assert.AreEqual(before, true);
            Assert.AreEqual(after, false);
        }

        [TestMethod]
        public void TestUpdateUser()
        {
            // given
            User u_old = test_users[3];
            User u_new = new User { Name = "UpdateTester", Password = "Alligator3" };

            // when
            bool before_old = dashboard.Login(u_old.Name, u_old.Password);
            bool before_new = dashboard.Login(u_new.Name, u_new.Password);
            dashboard.UpdateUser(u_new, u_old.Name, u_old.Password);
            bool after_old = dashboard.Login(u_old.Name, u_old.Password);
            bool after_new = dashboard.Login(u_new.Name, u_new.Password);

            // then
            Assert.AreEqual(true, before_old);
            Assert.AreEqual(false, before_new);
            Assert.AreEqual(false, after_old);
            Assert.AreEqual(true, after_new);
        }

        [TestMethod]
        public void TestStates()
        {
            // given
            IList<State> states = dashboard.States;
            IList<State> reference = new List<State>();
            reference.Add(new State { Name = "Burgenland" });
            reference.Add(new State { Name = "Kärnten" });
            reference.Add(new State { Name = "Oberösterreich" });
            reference.Add(new State { Name = "Niederösterreich" });
            reference.Add(new State { Name = "Steiermark" });
            reference.Add(new State { Name = "Salzburg" });
            reference.Add(new State { Name = "Tirol" });
            reference.Add(new State { Name = "Vorarlberg" });
            reference.Add(new State { Name = "Wien" });

            // when

            // then
            Assert.AreEqual(9, states.Count);
            foreach(State ref_state in reference)
            {
                Assert.AreEqual(true, states.Contains(ref_state));
            }
        }

        [TestMethod]
        public void TestDistricts()
        {
            // given
            IList<District> districts = dashboard.Districts;

            // when

            // then
            // it is stated that only 79 districts should exist, however that is the amount of POLITICAL districts.
            // 94 is the correct number
            Assert.AreEqual(94, districts.Count);
        }

        [TestCleanup]
        public void Cleanup()
        {
            dashboard.RemoveUser(test_users[2].Name, test_users[2].Password);
            dashboard.RemoveUser(test_users[3].Name, test_users[3].Password);
            dashboard.RemoveUser("UpdateTester", "Alligator3");
        }
    }
}
