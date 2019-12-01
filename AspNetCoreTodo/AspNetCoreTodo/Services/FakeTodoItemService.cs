using System;
using System.Threading.Tasks;
using AspNetCoreTodo.Models;
using Microsoft.AspNetCore.Identity;

namespace AspNetCoreTodo.Services
{
    public class FackTodoItemService : ITodoItemService
    {
        public Task<bool> AddItemAsync(TodoItem newItem, IdentityUser user)
        {
            throw new NotImplementedException();
        }

        public Task<TodoItem[]> GetIncompleteItemsAsync(IdentityUser user)
        {
            var item1 = new TodoItem
            {
                Title = "Learn ASP.NET CORE",
                DueAt = DateTimeOffset.Now.AddDays(1),
            };
            var item2 = new TodoItem
            {
                Title = "Build awesome apps",
                DueAt = DateTimeOffset.Now.AddDays(2),
            };

            return Task.FromResult(new[] { item1, item2 });
        }

        public Task<bool> MarkDoneAsync(Guid id, IdentityUser user)
        {
            throw new NotImplementedException();
        }
    }
}