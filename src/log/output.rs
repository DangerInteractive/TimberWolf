//! subsystem for log data output

macro_rules! write_log_event {
    ( $stream:expr, $event:ident ) => {
        writeln!(
            $stream,
            "{year:04}-{month:02}-{day:02} {hour:02}:{minute:02}:{second:02} {severity:<7} -> {context:<8}: {message}",
            year = &$event.time.year(),
            month = &$event.time.month(),
            day = &$event.time.day(),
            hour = &$event.time.hour(),
            minute = &$event.time.minute(),
            second = &$event.time.second(),
            severity = match &$event.severity {
                Severity::Debug => "Debug",
                Severity::Verbose => "Verbose",
                Severity::Info => "Info",
                Severity::Warning => "Warning",
                Severity::Error => "Error",
                Severity::Fatal => "Fatal",
            },
            context = &$event.context,
            message = &$event.message
        )
    };
}

/// subsystem for printing log data to strings
pub mod string {
    use super::super::event::{Event, Severity};
    use chrono::{Datelike, Timelike};
    use std::io::Write;

    /// write a log event to a character vector
    pub fn format_event(event: &Event) -> Vec<u8> {
        let mut stream = Vec::new();
        let _ = write_log_event!(&mut stream, event);
        stream
    }
}

/// subsystem for printing log data to the console
pub mod console {
    use super::super::event::{Event, Severity};
    use chrono::{Datelike, Timelike};
    use std::io::Write;

    /// write a log event to the console (stdout or stderr, depending on severity)
    pub fn write_event(event: &Event) -> std::result::Result<(), std::io::Error> {
        match &event.severity {
            Severity::Debug | Severity::Verbose | Severity::Info | Severity::Warning => {
                write_log_event!(std::io::stdout(), event)
            }
            Severity::Error | Severity::Fatal => write_log_event!(std::io::stderr(), event),
        }
    }
}
