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
            // V1: By hand
            //return new SimpleCurrencyConverter();
            // V2: XMLBased
            //return new XmlBasedCurrencyConverter();
            // V3: ADO.NET
            return new SQLeBasedCurrencyConverter();
        }
    }
}
