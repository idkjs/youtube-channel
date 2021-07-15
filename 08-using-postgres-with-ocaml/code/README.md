esy b dune build -w

```sh
docker run --name using-ocaml-with-postgres -p 5432:5432 -e POSTGRES_PASSWORD=password -d postgres
```
## Check if postgres is running

```sh
telnet localhost
nc localhost 5432
```
