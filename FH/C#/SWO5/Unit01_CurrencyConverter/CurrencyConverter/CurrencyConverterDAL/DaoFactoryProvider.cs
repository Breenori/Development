using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public class DaoFactoryProvider
    {
        private static IDaoFactory daoFactory;
        public static IDaoFactory GetDaoFactory()
        {
            if(daoFactory == null)
            {
                InitializeFactory();
            }
            return daoFactory;
        }

        private static void InitializeFactory()
        {
            Assembly asm = Assembly.LoadFrom(@"C:\Development\FH\C#\SWO5\Unit01_CurrencyConverter\CurrencyConverter\CurrencyConverterDALSQLe\bin\Debug\net5.0\CurrencyConverterDALSQLe.dll");
            var factories = asm.GetTypes().Where(type => type.GetCustomAttribute(typeof(DaoFactoryCandidate)) != null);
            if(!factories.Any())
            {
                throw new ArgumentException("No valid DAO factories were found.");
            } else if (factories.Count() > 1)
            {
                throw new ArgumentException("Multiple factories found!");
            }

            // get exact class of which the attribute is fitting
            Type factory = factories.Single();
            DaoFactoryCandidate candidateAttr = (DaoFactoryCandidate)factory.GetCustomAttribute(typeof(DaoFactoryCandidate));

            // now instanciate the class using 
            daoFactory = (IDaoFactory)Activator.CreateInstance(factory);
            Console.WriteLine($"Using database factory for provider {candidateAttr.ProviderName}");
        }
    }

}
