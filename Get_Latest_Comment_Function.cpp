let
    // Define the function with a parameter
    FetchLatestComment = (workItemId as number) as text =>
        let
            // Fetch the JSON document using the comments URL
            GetComments = Json.Document(VSTS.Contents(Text.Format("https://dev.azure.com/[Organization]/[Project]/_apis/wit/workItems/#{0}/comments?orderBy=createdDate desc&$top=1", {workItemId}))),
            // Access the comments list from the correct field
            CommentsList = GetComments[comments],
            // Check if the comments list is empty
            LatestComment = if List.IsEmpty(CommentsList) then "No comments" else CommentsList{0}[text]
        in
            LatestComment
in
    FetchLatestComment