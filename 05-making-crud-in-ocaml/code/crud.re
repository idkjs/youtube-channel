open Opium;

[@deriving yojson]
type message = {
  user_name: string,
  body: string,
};

let messages = ref([]);
let read_all_messages =
  App.get("/messages", _request => {
    let messages = messages^;
    let json = [%to_yojson: list(message)](messages);
    Lwt.return(Response.of_json(json));
  });
// let read_all_messages =
//   App.get("/messages", _ => Lwt.return(Response.of_plain_text("x")));
// produces: empty json list: []
let () = App.empty |> read_all_messages |> App.run_multicore;
