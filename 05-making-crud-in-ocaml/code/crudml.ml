open Opium

(* monadic let helper *)
let ( let* ) = Lwt.bind

type message = { user_name : string; body : string } [@@deriving yojson]

let messages = ref []

let read_all_messages =
  App.get "/messages" (fun _request ->
      let messages = !messages in
      let json = [%to_yojson: message list] messages in
      Lwt.return (Response.of_json json))

let post_message =
  App.post "/messages" (fun request ->
      let* input_json = Request.to_json_exn request in
      let input_message =
        match message_of_yojson input_json with
        | Ok message -> message
        | Error error -> raise (Invalid_argument error)
      in
      messages := input_message :: !messages;

      Lwt.return (Response.make ~status:`OK ()))
let () = App.empty |> read_all_messages |> post_message |> App.run_multicore
