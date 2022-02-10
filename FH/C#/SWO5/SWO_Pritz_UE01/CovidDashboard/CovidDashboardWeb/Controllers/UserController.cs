using Microsoft.AspNetCore.Mvc;
using SWO5.Dashboard.Domain;
using SWO5.Dashboard.Logic;
using SWO5.Dashboard.Web.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Web.Controllers
{
    public class UserController : Controller
    {
        private IManager<User> userManager = CovidDashboardFactory.CreateUserManager();
        private IManager<Report> reportManager = CovidDashboardFactory.CreateReportManager();
        private SHA256 sha256 = SHA256.Create();

        public IActionResult Index()
        {
            return View(userManager.FindAll());
        }
        public IActionResult Create()
        {
            UserViewModel uvm = new UserViewModel();
            uvm.User = new User();
            uvm.OldPassword = "";
            uvm.NewPassword = "";
            return View(uvm);
        }

        [HttpPost]
        public IActionResult Create(UserViewModel uvm)
        {
            if (ModelState.IsValid)
            {
                if (!uvm.User.Password.Equals(uvm.ConfirmPassword))
                {
                    ModelState.AddModelError("error", $"Passwords do not match.");
                    return View(uvm);
                }

                uvm.User.Password = getHash(uvm.User.Password);
                userManager.Create(uvm.User);
                return RedirectToAction("Index", "User");
            } else
            {
                return View(uvm);
            }
        }

        public IActionResult Edit(int id)
        {
            UserViewModel uvm = new UserViewModel();
            uvm.User = userManager.FindById(id);
            uvm.OldPassword = "";
            uvm.NewPassword = "";
            return View(uvm);
        }
        private String getHash(String pwd)
        {
            byte[] bytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(pwd));
            StringBuilder builder = new StringBuilder();
            for (int i = 0; i < bytes.Length; i++)
            {
                builder.Append(bytes[i].ToString("x2"));
            }
            return builder.ToString();
        }

        [HttpPost]
        public IActionResult Edit(UserViewModel uvm)
        {
            if (ModelState.IsValid)
            {
                if (uvm.OldPassword == null)
                {
                    ModelState.AddModelError("error", $"Existing password must be entered to change data for this user.");
                    return View(uvm);
                }
                uvm.OldPassword = getHash(uvm.OldPassword);
                if (!uvm.User.Password.Equals(uvm.OldPassword))
                {
                    ModelState.AddModelError("error", $"Old password was not correct!");
                    return View(uvm);
                }
                else if (uvm.NewPassword != null && uvm.NewPassword.Length != 0 && uvm.NewPassword.Length < 6)
                {
                    ModelState.AddModelError("error", $"New password must at least have 6 characters or be empty if you don't want to change it!");
                    return View(uvm);
                }

                if (uvm.NewPassword != null && uvm.NewPassword.Length != 0)
                {
                    uvm.User.Password = getHash(uvm.NewPassword);
                }
                userManager.Update(uvm.User);
                return RedirectToAction("Index", "User");
            }
            else
            {
                return View(uvm);
            }
        }

        public IActionResult Delete(int id)
        {
            User user = userManager.FindById(id);
            return View(user);
        }

        [HttpPost]
        public IActionResult Delete(User user)
        {
            if (reportManager.FindAll().Where(r => r.FromUser.Id == user.Id).Count() > 0)
            {
                ModelState.AddModelError("error", $"The user '{user.Name}' cannot be deleted since it is being referenced in one or more reports.");
            }

            if (ModelState.IsValid)
            {
                userManager.Delete(user);
                return RedirectToAction("Index", "User");
            }
            else
            {
                return View(user);
            }
        }
    }
}
