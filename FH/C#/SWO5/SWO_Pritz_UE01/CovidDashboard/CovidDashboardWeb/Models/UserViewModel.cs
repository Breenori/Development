using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Web.Models
{
    public class UserViewModel
    {
        public User User { get; set; }

        [DisplayName("Old Password")]
        public String OldPassword { get; set; }
        [DisplayName("New Password")]
        public String NewPassword {get;set;}
        [DisplayName("Confirm Password")]
        public String ConfirmPassword { get; set; }
    }
}
