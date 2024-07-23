let
    // Define the function with a parameter
    FetchAcceptanceCriteria = (workItemId as number) as text =>
        let
            // Fetch the JSON document using the dynamic URL
            GetDocument = Json.Document(VSTS.Contents(Text.Format("https://dev.azure.com/[Organization]/[Project]/_apis/wit/workitems/#{0}", {workItemId}))),
            // Convert to table
            ConvertToTable = Record.ToTable(GetDocument[fields]),
            // Transpose the table to switch rows and columns
            TransposedTable = Table.Transpose(ConvertToTable),
            // Promote the first row to headers
            PromotedHeaders = Table.PromoteHeaders(TransposedTable, [PromoteAllScalars=true]),
            // Attempt to fetch 'Microsoft.VSTS.Common.AcceptanceCriteria' and handle possible errors
            AcceptanceCriteriaResult = try PromotedHeaders[Microsoft.VSTS.Common.AcceptanceCriteria]{0} otherwise "0"
        in
            AcceptanceCriteriaResult
in
    FetchAcceptanceCriteria