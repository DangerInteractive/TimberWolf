extern crate chrono;

use crate::log::event::{Event, Severity};
use crate::log::output::string::format_event;
use chrono::DateTime;

#[test]
fn test_log_event_to_string () {

    let time = match DateTime::parse_from_rfc3339("2019-01-29T21:09:30+00:00") {
        Ok(time) => time,
        Err(_error) => {
            panic!("failed to parse time");
        }
    };
    let event = Event::with_time(time, Severity::Debug, "test", "this is a test message");
    let string = format_event(&event);
    let string = match std::str::from_utf8(&string) {
        Ok(value) => value,
        Err(_error) => {
            panic!("failed to parse UTF-8");
        }
    };

    let prototype = "2019-01-29 21:09:30 Debug   -> test    : this is a test message\n";

    assert_eq!(prototype, string);

}
