#!/usr/bin/env python2
#
# Copyright (C) Microsoft Corporation, All rights reserved.

"""JRDSClient class."""

from datetime import datetime

import configuration
from workerexception import *


class JRDSClient:
    def __init__(self, http_client):
        self.httpClient = http_client
        self.protocol_version = "1.0"
        self.base_uri = configuration.get_jrds_base_uri()
        self.account_id = configuration.get_account_id()
        self.HybridWorkerGroupName = configuration.get_hybrid_worker_name()
        self.machine_id = configuration.get_machine_id()

    def get_sandbox_actions(self):
        """Gets any pending sandbox actions.

        Returns:
            A list of sandbox actions.

        Note:
            The output list is of the following format:
            [
                {
                    "SandboxId": "206738c8-b66a-4eee-95a6-ddc23e3833a9",
                    "ConnectionEndpoint": "",
                    "ConnectionPort": 0,
                    "SandboxCookie": "nQwdpZ3MK5s=",
                    "CredentialName": null
                }
            ]
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + \
              "/Sandboxes/GetSandboxActions?HybridWorkerGroupName=" + self.HybridWorkerGroupName + \
              "&api-version=" + self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data["value"]
        raise Exception("Unable to get sandbox actions. [status=" + str(request.status_code) + "]")

    def get_job_actions(self, sandbox_id):
        """Gets any pending job action for the given sandbox id.

        Args:
            sandbox_id: string, the sandbox id.

        Returns:
            A list of job actions.

        Note:
            The output list is of the following format:
            [
                {
                    "MessageMetadata": {
                        "PopReceipt": "AgAAAAMAAAAAAAAAPuDINxcZ0gE=",
                        "MessageId": "2e682df3-a6c6-4d23-afc2-40dc01c2a509"
                    },
                    "MessageSource'": "Queue",
                    "LockToken'": "00000000-0000-0000-0000-000000000000",
                    "JobId'": "6cbb98cc-d69a-46f0-a116-3b6094ceba6b"
                }
            ]
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/Sandboxes/" + sandbox_id + \
              "/jobs/getJobActions?api-version=" + self.protocol_version
        request = self.httpClient.get(url)

        # Stale sandbox
        if request.status_code == 401:
            raise JrdsSandboxTerminated()

        if request.status_code == 200:
            job_actions = request.deserialized_data["value"]
            if len(job_actions) != 0:
                message_metadatas = [action["MessageMetadata"] for action in job_actions]
                self.acknowledge_job_action(sandbox_id, message_metadatas)
            return job_actions
        raise Exception("Unable to get job actions. [status=" + str(request.status_code) + "]")

    def get_job_data(self, job_id):
        """Get the job details for the given id.

        Args:
            job_id: string, the job id.

        Returns:
            A dictionary containing the job's details.

        Note:
            The output dictionary is of the following format:
            {
                "creationTime": "2016-08-02T22:19:40.39+00:00",
                "endTime": null,
                "startRequestTime": "2016-08-02T22:19:42.597+00:00",
                "jobId": "324e3d65-cae4-4136-b953-7f001f92be13",
                "jobKey": 1341273,
                "jobStatus": 0,
                "triggerScope": 0,
                "jobStatusDetails": 0,
                "lastModifiedTime": "2016-08-02T22:19:40.39+00:00",
                "lastStatusModifiedTime": null,
                "partitionId": 1933161748,
                "parameters": null,
                "invokedRunbookVersions": [],
                "pendingAction": 1,
                "pendingActionData": null,
                "runbookVersionId": "ccb7bc90-20e9-4e5c-bbf0-f265c1de79e6",
                "runbookVersion": "16_2016-06-08T21:27:41.7600000",
                "startTime": null,
                "accountId": "726169cd-9760-46ec-a7a8-ea1c7b4be12b",
                "workflowInstanceId": null,
                "runbookVersionKey": 1198942,
                "runbookKey": 632266,
                "accountKey": 794179,
                "jobException": null,
                "moduleInfo": [
                    {
                        "isGlobal": true,
                        "moduleId": "cb28147b-7933-4fcf-bdf0-bae57571113b",
                        "moduleVersionId": "d5939764-956e-4d99-826a-2e2d24d2ee34",
                        "name": "Azure",
                        "versionKey": 94261
                    },
                    {
                        "isGlobal": true,
                        "moduleId": "b553579f-f545-4295-843b-dfe2e32447e2",
                        "moduleVersionId": "e23c5e08-deaf-4237-b21a-6122a5245ad0",
                        "name": "Microsoft.PowerShell.Core",
                        "versionKey": 94262
                    }
                ],
                "fullWorkflowScript": null,
                "trackingId": "43d2fbbd-bdde-4e9a-840c-eb5a3c634004",
                "subscriptionId": "1d8225ca-97d3-4628-b657-fbb2e0609287",
                "noPersistEvictionsCount": 0,
                "status": null,
                "runOn": "WindowsWorkerGroup",
                "tierName": "Basic",
                "accountName": "PythonTest",
                "triggerSource": 1
            }
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/jobs/" + job_id + "?api-version=" + \
              self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data
        raise Exception("Unable to get job. [status=" + str(request.status_code) + "]")

    def get_job_updatable_data(self, job_id):
        """Gets the job updatable data for the given id.

        Args:
            job_id: string, the job id.

        Returns:
            A dictionary containing the job's updatable data.

        Note:
            The output dictionary is of the following format:
            {
                "logActivityTrace": 0,
                "triggerSource": 1,
                "jobId": "d894d142-29f2-4f8c-85cd-f2f3c54c5f00",
                "logProgress": false,
                "jobStatus": 3,
                "accountName": "PythonTest",
                "partitionId": 1294079927,
                "logDebug": false,
                "isDraft": false,
                "workflowInstanceId": None,
                "JobKey": 1367376,
                "subscriptionId": "1d8225ca-97d3-4628-b657-fbb2e0609287",
                "noPersistEvictionsCount": 0,
                "AccountKey": 794179,
                "jobStartedBy": "live.com#oaastestdf01@live.com",
                "jobRunDestination": "WindowsWorkerGroup",
                "tierName": "u'Basic'",
                "pendingActionData": None,
                "jobStatusDetails": 0,
                "resourceGroupName": "PythonTest",
                "pendingAction": 0,
                "logVerbose": false,
                "RunbookKey": 632266
            }
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/jobs/" + job_id + \
              "/getUpdatableData?api-version=" + self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data
        raise Exception("Unable to get job. [status=" + str(request.status_code) + "]")

    def get_runbook_data(self, runbook_version_id):
        """Gets the runbook definition of the given runbook_version_id.

        Args:
            runbook_version_id: string, the runbook version id.

        Returns:
            A dictionary containing the runbook's details.

        Note:
            The output list is of the following format:
            {
                "name": "594D5915-57D6-40C3-A8C1-6112C8B25900ForPython",
                "accountId": "726169cd-9760-46ec-a7a8-ea1c7b4be12b",
                "runbookId": "98a55667-7bb9-4feb-acac-ba4664987e9d",
                "definition": "#python\r\nimport platform\r\n\r\nprint \"OS : \" + platform.system(),
                               platform.release()\r\nprint \"Helloworld from Python\"",
                "runbookDefinitionKind": 5,
                "runbookVersionId": "ccb7bc90-20e9-4e5c-bbf0-f265c1de79e6",
                "parameters": null
            }
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/runbooks/" + runbook_version_id + \
              "?api-version=" + self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data
        raise Exception("Unable to get runbook. [status=" + str(request.status_code) + "]")

    def get_variable_asset(self, name):
        """Gets the requested automation variable asset.

        Args:
            name : Name of the automation variable.

        Note:
            The output list is of the following format:
            {
                "isEncrypted": false,
                "name": "testvar",
                "value": "Value of variable"
            }
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/variables/" + name + "?api-version=" \
              + self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data
        raise Exception("Unable to get variable asset. [status=" + str(request.status_code) + "]")

    def get_credential_asset(self, name):
        """Gets the requested automation credential asset.

        Args:
            name : Name of the automation credential.

        Note:
            The output list is of the following format:
            {
                "userName": "myusername",
                "name": "testcred",
                "value": "mypassword",
                "description": "None"
            }
        """
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/credentials/" + name + "?api-version=" \
              + self.protocol_version
        request = self.httpClient.get(url)

        if request.status_code == 200:
            return request.deserialized_data
        raise Exception("Unable to get credential asset. [status=" + str(request.status_code) + "]")

    def acknowledge_job_action(self, sandbox_id, message_metadatas):
        """Acknowledges the job action.

        Args:
            sandbox_id  : string        , the sandbox id.
            lock_tokens : array(string) , the lock tokens.
        """
        payload = {'MessageMetadatas': message_metadatas}
        headers = {"Content-Type": "application/json"}
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/Sandboxes/" + sandbox_id + \
              "/jobs/AcknowledgeJobActions?api-version=" + self.protocol_version
        request = self.httpClient.post(url, headers=headers, data=payload)

        if request.status_code == 200:
            return
        raise Exception("Unable to acknowledge job action. [status=" + str(request.status_code) + "]")

    def set_job_status(self, sandbox_id, job_id, job_status, is_terminal, exception=None):
        """Set the job status of the given job id (and exception if needed).

        Args:
            sandbox_id  : string    , the sandbox id.
            job_id      : string    , the job id.
            job_status  : string    , the job status.
            is_terminal : boolean   , is the job status terminal value.
            exception   : string    , the exception details (optional).
        """
        payload = {'exception': exception,
                   'isFinalStatus': is_terminal,
                   'jobStatus': job_status}
        headers = {"Content-Type": "application/json"}
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/Sandboxes/" + sandbox_id + "/jobs/" + \
              job_id + "/changeStatus?api-version=" + self.protocol_version
        request = self.httpClient.post(url, headers=headers, data=payload)

        if request.status_code == 200:
            return
        raise Exception("Unable to set job status. [status=" + str(request.status_code) + "]")

    def set_stream(self, job_id, runbook_version_id, stream_text, stream_type, sequence_number):
        """Set the streams for the given job id.

        Args:
            job_id              : string, the job id.
            runbook_version_id  : string, the runbook version id.
            stream_text         : string, the stream text.
            stream_type         : string, the stream type (Progress, Output, Warning, Error, Debug, Verbose, Any).
            sequence_number     : int   , the stream index in sequence.
        """
        payload = {'AccountId': self.account_id,
                   'JobId': job_id,
                   'RecordTime': datetime.now().isoformat(),
                   'RunbookVersionId': runbook_version_id,
                   'SequenceNumber': sequence_number,
                   'StreamRecord': None,
                   'StreamRecordText': stream_text,
                   'Type': stream_type}
        headers = {"Content-Type": "application/json"}
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/jobs/" + job_id + \
              "/postJobStream?api-version=" + self.protocol_version
        request = self.httpClient.post(url, headers=headers, data=payload)

        if request.status_code == 200:
            return
        raise Exception("Unable to set streams. [status=" + str(request.status_code) + "]")

    def set_log(self, event_id, activity_id, log_type, args):
        """Set the log (generate a corresponding ETW trace on the JRDS worker).

        Args:
            event_id    : int           , the event id.
            activity_id : string        , the activity id.
            log_type    : string        , the log type (Debug/Informational).
            args        : array(object) , the trace arguments.
        """
        payload = {'activityId': activity_id,
                   'args': args,
                   'eventId': event_id,
                   'logtype': log_type}
        headers = {"Content-Type": "application/json"}
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/logs?api-version=" + self.protocol_version
        request = self.httpClient.post(url, headers=headers, data=payload)

        if request.status_code == 200:
            return
        raise Exception("Unable to set log. [status=" + str(request.status_code) + "]")

    def unload_job(self, subscription_id, sandbox_id, job_id, is_test, start_time, execution_time):
        """Unloads the job for the given job id.

        Args:
            sandbox_id      : string    , the sandbox id.
            job_id          : string    , the job id.
            is_test         : boolean   , is test job.
            start_time      : datetime  , the job status.
            execution_time  : int       , the job execution time in seconds.
        """
        payload = {'executionTimeInSeconds': execution_time,
                   'isTest': is_test,
                   'jobId': job_id,
                   'startTime': start_time.isoformat(),
                   'subscriptionId': subscription_id}
        headers = {"Content-Type": "application/json"}
        url = self.base_uri + "/automationAccounts/" + self.account_id + "/Sandboxes/" + sandbox_id + "/jobs/" + \
              job_id + "/unload?api-version=" + self.protocol_version
        request = self.httpClient.post(url, headers=headers, data=payload)

        if request.status_code == 200:
            return
        raise Exception("Unable to unload job. [status=" + str(request.status_code) + "]")
