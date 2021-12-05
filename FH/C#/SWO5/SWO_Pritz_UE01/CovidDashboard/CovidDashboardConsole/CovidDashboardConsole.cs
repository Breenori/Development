using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using System;
using System.Collections.Generic;

namespace CovidDashboardConsole
{
    class CovidDashboardConsole
    {
        static void Main(string[] args)
        {
            ICovidDashboard dashboard = new SQLeBasedCovidDashboard();
            //dashboard.FillFromCSV(@"../../../../CovidFaelle_Timeline_GKZ.csv");
            Console.WriteLine("Database setup completed.");
            var result = dashboard.GetReportsForDistrict("Wien", DateTime.Parse("14.10.2020"), DateTime.Parse("24.12.2020"));

            dashboard.AddUser("Sebi", "geheim");


            User u = new User
            {
               Name = "Sebibebi",
               Password = "geheim2"
            };

            dashboard.UpdateUser(u, "Sebi", "geheim");

            dashboard.Login("Sebibebi", "geheim2");
            Console.WriteLine($"Current User: {dashboard.LoggedInUser}");

            dashboard.RemoveUser("Sebibebi", "geheim2");
            Console.WriteLine($"Current User: {dashboard.LoggedInUser}");


            Console.WriteLine("End");
            IList<District> districts = dashboard.Districts;
        }
    }
}
