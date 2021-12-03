using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public class DaoFactoryProvider
    {
        private static IDaoFactory daoFactory;
        private const string ASSEMBLY_PATH = @"D:\Projects\Git\Development\FH\C#\SWO5\SWO_Pritz_UE01\CovidDashboardLogic\CovidDashboardDALSQLe\bin\Debug\net5.0\CovidDashboardDALSQLe.dll";
    
        private static void InitializeFactory()
        {
            Assembly asm = Assembly.LoadFrom(ASSEMBLY_PATH);
            var factories = asm.GetTypes().Where(type => type.GetCustomAttribute(typeof(DaoFactoryCandidate)) != null);

            if(!factories.Any())
            {
                throw new ArgumentException("No valid DaoFactory found!");
            }
            else if(factories.Count() > 1)
            {
                throw new ArgumentException("More than one factory found!");
            }

            Type factory = factories.Single();
            DaoFactoryCandidate candidateAttr = (DaoFactoryCandidate)factory.GetCustomAttribute(typeof(DaoFactoryCandidate));
            daoFactory = (IDaoFactory)Activator.CreateInstance(factory);
            Console.WriteLine($"Using {candidateAttr.ProviderName} as database provider. ");
        }

        public static IDaoFactory GetDaoFactory()
        {
            if(daoFactory == null)
            {
                InitializeFactory();
            }
            return daoFactory;
        }
    }
}
