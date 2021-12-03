﻿using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface ICountryDao : IDao<Country>
    {
        IList<Country> ReadForCurrencyType(CurrencyType currencyType); 
    }
}
