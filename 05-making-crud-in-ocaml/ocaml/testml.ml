open Lwt
open Cohttp
open Cohttp_lwt_unix

let postData = ref "{\"user_name\":\"mando\",\"body\":\"YES2!\"}";;

let reqBody =
  let uri = Uri.of_string "localhost:3000/messages" in
  let headers = Header.init ()
    |> fun h -> Header.add h "Content-Type" "application/json"
  in
  let body = Cohttp_lwt.Body.of_string !postData in

  Client.call ~headers ~body `POST uri >>= fun (_resp, body) ->
  body |> Cohttp_lwt.Body.to_string >|= fun body -> body

let () =
  let respBody = Lwt_main.run reqBody in
  print_endline (respBody)
