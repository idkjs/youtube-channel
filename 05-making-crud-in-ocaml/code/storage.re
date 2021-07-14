[@deriving yojson]
type message = {
  user_name: string,
  body: string,
};

let messages = ref([]);

let read_all_messages = () => Lwt.return(messages^);

let insert_message = message => messages := [message, ...messages^];
