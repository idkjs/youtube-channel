// open Opium;

// [@deriving yojson]
// type message = {
//   user_name: string,
//   body: string,
// };

// let messages = ref([]);
// let read_all_messages =
//   App.get("/messages", _request => {
//     let messages = messages^;
//     let json = [%to_yojson: list(message)](messages);
//     Lwt.return(Response.of_json(json));
//   });
// // let read_all_messages =
// //   App.get("/messages", _ => Lwt.return(Response.of_plain_text("x")));
// // produces: empty json list: []
// let () = App.empty |> read_all_messages |> App.run_multicore;
open Opium;

/* monadic let helper */
let ( let* ) = Lwt.bind;

// [@deriving yojson]
// type message = {
//   user_name: string,
//   body: string,
// };

// let messages = ref([]);

let read_all_messages =
  App.get("/messages", _request => {
    let* messages = Storage.read_all_messages();
    let json = [%to_yojson: list(Storage.message)](messages);
    Lwt.return(Response.of_json(json));
  });

let post_message =
  App.post("/messages", request => {
    let* input_json = Request.to_json_exn(request);
    let input_message =
      switch (Storage.message_of_yojson(input_json)) {
      | Ok(message) => message
      | Error(error) => raise(Invalid_argument(error))
      };

    // messages := [input_message, ...messages^];
    let* () = Storage.insert_message(input_message);
    Lwt.return(Response.make(~status=`OK, ()));
  });
// run multi_core doesnt work without db
// let () = App.empty |> read_all_messages |> post_message |> App.run_multicore;
let () = App.empty |> read_all_messages |> post_message |> App.run_command;
