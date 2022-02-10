using Microsoft.AspNetCore.Mvc.Rendering;
using SWO5.Dashboard.Domain;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Web.Models
{
    public class DistrictViewModel
    {
        public District District { get; set; }
        public List<SelectListItem> AvailableStates { get; set; }
        [Required(ErrorMessage = "Please select a State.")]
        public long SelectedStateId {get;set;}

    }
}
