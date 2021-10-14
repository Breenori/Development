using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.Logic
{
    public class CurrencyConverterFactory
    {
        public static ICurrencyConverter CreateCurrencyConverter()
        {
            return new SimpleCurrencyConverter();
        }
    }
}
