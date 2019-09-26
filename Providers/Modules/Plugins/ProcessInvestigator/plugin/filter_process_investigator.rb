require_relative 'process_investigator_lib'
require_relative 'oms_common' 

module Fluent
  class ProcessInvestigatorFilter < Filter

    Fluent::Plugin.register_filter('filter_process_investigator', self)

    def configure(conf)
        super
        # Do the usual configuration here
    end

    def start
        super
        # This is the first method to be called when it starts running
        # Use it to allocate resources, etc.
    end

    def shutdown
        super
        # This method is called when Fluentd is shutting down.
        # Use it to free up resources, etc.
    end

    def filter(tag, time, record)       
        process_investigator = OMS::ProcessInvestigator.new(@log)
        process_investigator_blob = process_investigator.transform_and_wrap(record)

        return process_investigator_blob
    end # filter
  end # class
end # module
