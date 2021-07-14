open Opium

type message = { user_name : string; body : string } [@@deriving yojson]

let messages = ref []

let read_all_messages =
  App.get "/messages" (fun _request ->
      let messages = !messages in
      let json = [%to_yojson: message list] messages in
      Lwt.return (Response.of_json json))
