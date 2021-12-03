using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.DAL
{
    public interface IDao<T>
    {
        T ReadForIdentity(long id);
        IList<T> ReadAll();
        long Create(T entity);
        long Update(T entity);
        bool Delete(long id);

        void fillFromCSV(string filename);
    }
}
