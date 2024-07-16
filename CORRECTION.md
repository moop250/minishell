# Shutdown readline leaks warnings in valgrind

```bash
echo "{                                                                                  
   readline
   Memcheck:Leak
   ...
   fun:readline
}
{
   add_history
   Memcheck:Leak
   ...
   fun:add_history
}" > readline.supp
```

`valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell`
