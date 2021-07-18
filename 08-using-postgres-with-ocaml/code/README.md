esy b dune build -w

```sh
docker run --name using-ocaml-with-postgres -p 5432:5432 -e POSTGRES_PASSWORD=password -d postgres
```
## Check if postgres is running

```sh
telnet localhost
nc localhost 5432
```

```sh
> psql -d ocaml_messages_db -f init.sql
CREATE EXTENSION
CREATE TABLE
psql:backend/db/migrations.sql:10: NOTICE:  relation "migrations" already exists, skipping
CREATE TABLE
```
db url: `postgres://admin_user@localhost/counters_db`
