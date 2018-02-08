let handleClick = (text) => {
  Js.log(text)
};

let component = ReasonReact.statelessComponent("App");
let make = (_children) => {
  ...component,
  render: (_self) =>
    <div>
      <Controls.Controls onSubmit=handleClick />
      <section>
        (ReasonReact.stringToElement("hello"))
      </section>
    </div>
};
