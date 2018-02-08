
let valueFromEvent = (evt) : string => (
    evt
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
  )##value;


module Controls = {
    type state = string;
    type action =
      | SyncText(string)
      | Submit(string);

    let component = ReasonReact.reducerComponent("Controls");
    let make = (~onSubmit, _children) => {
        ...component,
        initialState: () => "",
        reducer: (action, _text) => switch action {
        | SyncText(text) => ReasonReact.Update(text)
        | Submit(text) =>
            onSubmit(text);
            ReasonReact.Update("");
        },
        render: ({ state: text, reduce }) =>
            <section id="controls">
                <input
                    value=text
                    _type="text"
                    placeholder="Search..."
                    onChange=((reduce((event) => SyncText(valueFromEvent(event)))))
                    onKeyDown=((event) =>
                        if (ReactEventRe.Keyboard.key(event) == "Enter") {
                            (reduce(() => Submit(text)))()
                        }
                    )
                />
                <button onClick=(reduce((_e) => Submit(text)))>(ReasonReact.stringToElement("Search"))</button>
            </section>
    }
}