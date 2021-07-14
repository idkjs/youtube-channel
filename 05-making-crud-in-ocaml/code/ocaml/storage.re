[@deriving yojson]
type message = {
  user_name: string,
  body: string,
};

let ( let* ) = Lwt.bind;

let database_file = "messages.json";

let read_all_messages = () =>
  Lwt_io.with_file(
    ~mode=Input,
    database_file,
    input_channel => {
      let* database_string =
        Lwt_io.read_lines(input_channel) |> Lwt_stream.to_list;
      let database_json =
        Yojson.Safe.from_string(String.concat("\n", database_string));

      switch ([%of_yojson: list(message)](database_json)) {
      | Ok(messages) => Lwt.return(messages)
      | Error(error) => raise(Invalid_argument(error))
      };
    },
  );

let insert_message = message => {
  let* messages = read_all_messages();
  let messages = [message, ...messages];
  Lwt_io.with_file(
    ~mode=Output,
    database_file,
    output_channel => {
      let messages_string =
        messages
        |> [%to_yojson: list(message)]
        |> Yojson.Safe.pretty_to_string;

      Lwt_io.write(output_channel, messages_string);
    },
  );
};
