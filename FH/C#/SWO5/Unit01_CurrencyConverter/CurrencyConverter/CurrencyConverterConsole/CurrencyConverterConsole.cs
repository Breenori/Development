using System;
using System.Text;
using SWO5.Currency.Logic;

namespace SWO5.Currency.App
{


    class CurrencyConverterConsole
    {

        readonly ICurrencyConverter currencyConverter = CurrencyConverterFactory.CreateCurrencyConverter();

        // Nich erlaubt außerhalb von SWO5.Currency.Logic
        //ICurrencyConverter currencyConverter = new SimpleCurrencyConverter();

        static void Main(string[] args)
        {
            new CurrencyConverterConsole().RunConverter();
        }

        void RunConverter()
        {
            Console.WriteLine("Currency Converter");
            Console.WriteLine("How much money do you want to convert?:");

            //wirft ArgumentNullException bei null
            //double euro = Double.Parse(Console.ReadLine());
            //Console.WriteLine(euro);

            //liefert 0 bei null
            //euro = Convert.ToDouble(null);
            //Console.WriteLine(euro);

            if (!Double.TryParse(Console.ReadLine(), out double value))
            {
                Console.WriteLine("Please enter valid numbers only");
            }
            else
            {
                Console.WriteLine("Please enter a currency to convert from:");
                String currency = Console.ReadLine().ToUpper();

                if (currencyConverter.IsKnownCurrency(currency))
                {
                    double result = currencyConverter.ConvertToEuro(currency, value);
                    //Version 1
                    //Console.WriteLine(currency + ": " + value.ToString("0.00") + " corresponds to EUR: " + result.ToString("0.00"));
                    //Version 2
                    //StringBuilder builder = new StringBuilder();
                    //builder.Append(currency).Append(": ").Append(value.ToString("0.00")).Append(" corresponds to EUR: ").Append(result.ToString("0.00"));
                    //Console.WriteLine(builder.ToString());
                    //Version 3
                    //Console.OutputEncoding = Encoding.UTF8;
                    Console.WriteLine($"{currency}: {value:0.00} corresponds to EUR: {result:0.00}");
                    Console.Beep();
                    Console.ReadLine();

                    Console.WriteLine("How much money do you want to convert?:");
                    if (!Double.TryParse(Console.ReadLine(), out value))
                    {
                        Console.WriteLine("Please enter valid numbers only");
                    }
                    else
                    {
                        Console.WriteLine("Please enter a currency to convert from:");
                        String from = Console.ReadLine().ToUpper();
                        Console.WriteLine("Please enter a currency to convert to:");
                        String to = Console.ReadLine().ToUpper();
                        if (currencyConverter.IsKnownCurrency(from)
                                && currencyConverter.IsKnownCurrency(to))
                        {
                            result = currencyConverter.ConvertFromTo(from, to, value);
                            //variante 1
                            Console.WriteLine($"{from} : {value:0.00} corresponds to {to} : {result:0.00}");
                        }
                        else
                        {
                            Console.WriteLine("The supplied currency codes are not available");
                        }
                    }

                }
                else
                {
                    Console.WriteLine("The supplied currency code is not available");
                }
            }
        }


    }
}
