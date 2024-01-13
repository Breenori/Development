using SWO5.Currency.Domain;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Collections.Generic;

namespace SWO5.Currency.Web.Models
{
    public class ExchangeRateViewModel
    {
        public ExchangeRate ExchangeRate { get; set; }

        public List<SelectListItem> AvailableCurrencyTypes { get; set; }

        public long SelectedCurrencyTypeId { get; set; }
    }
}
