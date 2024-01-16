using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Dashboard.Logic
{
    public interface IManager<T>
    {
        T FindById(long identity);
        IList<T> FindAll();
        T Create(T entity);
        T Update(T entity);

        bool Delete(T entity);
    }
}
