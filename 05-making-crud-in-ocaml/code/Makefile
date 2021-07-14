.DEFAULT_GOAL := build

project_name = crud
opam_file = $(project_name).opam
DUNE = opam exec -- dune

.PHONY: build
build:
	# Build the app
	$(DUNE) build @all

.PHONY: install
install:
	# Install the dependencies
	opam install . --deps-only --with-doc --with-test -y

.PHONY: init
init:
	# Create a local opam switch and install deps
	opam switch create . ocaml-base-compiler.4.12.0 --deps-only --locked
	opam install -y ocaml-lsp-server reason
	make install

.PHONY: watch
watch:
	watchexec -w backend \
	--exts re,rei,ml,mli,atd,json -r -c \
	"clear; $(MAKE) run-debug"

.PHONY: fmt
fmt:
	# Format
	$(DUNE) build @fmt --auto-promote

.PHONY: test
test:
	# Run unit tests
	$(DUNE) test --force

.PHONY: run
run:
	$(DUNE) exec $(project_name)

.PHONY: run-debug
run-debug:
	$(DUNE) exec $(project_name) -- --debug

.PHONY: migrate
migrate:
	# Run the database migrations defined in migrate/migrate.ml
	$(DUNE) exec migrate

.PHONY: rollback
rollback:
	# Run the database rollback defined in migrate/rollback.ml
	$(DUNE) exec rollback

.PHONY: deps
# Alias to update the opam file and install the needed deps
deps: $(opam_file)

.PHONY: clean
clean:
	$(DUNE) clean

db_clean:
	@docker container ls -qa | xargs -n1 docker container stop
	@docker container ls -qa | xargs -n1 docker container rm
	@docker volume ls -q | xargs -n1 docker volume rm

db_down:
	@docker compose -f docker-compose.dev.yml down

db_up:
	@docker compose -f docker-compose.dev.yml -p $(project_name) up

# Update the package dependencies when new deps are added to dune-project
$(opam_file): dune-project
	$(DUNE) build @install # Update the $(project_name).opam file
	make install
