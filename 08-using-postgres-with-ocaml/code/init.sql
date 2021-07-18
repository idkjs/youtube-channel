-- This file is just for development
-- Heroku in this case creates the DB and users
SET client_encoding = 'UTF8';

CREATE USER admin_user WITH PASSWORD 'secret';
GRANT ALL PRIVILEGES ON DATABASE ocaml_messages_db TO admin_user;
ALTER ROLE admin_user SUPERUSER;
