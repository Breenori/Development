using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SWO5.Dashboard.API.Models
{
    public class UserModel
    {
        private static readonly IManager<User> userManager = CovidDashboardFactory.CreateUserManager();
        public static List<User> AvailableUsers => userManager.FindAll().ToList();
    }

}
